import subprocess as sp
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/prediction', methods=['POST'])
def compute_prediction():
    data = request.get_json()
    name = data['name']
    sequence = data['sequence'].upper()

    # Validate sequence here

    # Write the content to an input file
    with open('smirp/data/{}.fasta'.format(name), 'w') as input_file:
        input_file.write('>{}\n{}'.format(name, sequence))

    # Run the feature building script
    cmd = 'cd /app/smirp/ && python build_hmp_features.py -i {}.fasta -n 1'.format(name)
    sp.call(cmd, shell=True)

    # Run the model
    cmd = 'cd /app/smirp/ && python predict.py -i {}.fasta.hmp20 -m {}'.format(name, 'drosophila')
    sp.call(cmd, shell=True)

    with open('/app/smirp/data/{}.fasta.hmp20.results'.format(name)) as results:
        score = results.read().split('\n')[1].split()[1]
        return score

    return 'Computing prediction...'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3001)
