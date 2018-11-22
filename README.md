## To run SMIRP

To run SMIRP, you will need to install docker and docker-compose. That's it. Once you have that, do the following:

```
$ docker-compose build
$ docker-compose up -d
```

Docker will take care of installing the correct dependencies and linking all the files for you. SMIRP is now accepting request at port 3001.

You can request SMIRP's predictions by simply making a POST request:
```
curl http://localhost:3001/prediction -X POST -H "Content-Type: application/json" \
-d '{"name": "franktest", 
"sequence": "CCUGCUGGCUACUGCUGACGACUGCUCUGACUUUAUUGCACUACUGUACUGUACAGCUAGCAGUGCAAUAGUAUUGUCAAAGCAUCCGGGAGCAGGCUAC"}'
```

As simple as that. Of course, you will want to route incoming traffic so that it reaches this app running at port 3001 if apps come over the internet over port 80. This can be done easily with Apache.
