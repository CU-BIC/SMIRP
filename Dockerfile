# SRUNtart from a standard Python 3 image
FROM python:2

# Update pip
RUN pip install --upgrade pip

# Make 32-bit code executable
RUN dpkg --add-architecture i386
RUN apt update
RUN apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386

# Install java
RUN apt install -y default-jre

# Install perl
RUN wget http://www.cpan.org/src/perl-5.14.2.tar.gz
RUN tar -xzvf perl-5.14.2.tar.gz

# Build perl
WORKDIR /perl-5.14.2/
RUN ./Configure -des -Dprefix=/usr/local -Dusethreads
RUN make
RUN make install

# Clean
WORKDIR /
RUN rm -rf perl-5.14.2
RUN rm perl-5.14.2.tar.gz

# Install flask
RUN pip install flask

# Move into the app dir
WORKDIR /app/

EXPOSE 3001

CMD ["python", "app.py"]
