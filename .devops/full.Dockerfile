ARG UBUNTU_VERSION=22.04

FROM ubuntu:$UBUNTU_VERSION as build

RUN apt-get update && \
    apt-get install -y build-essential python3 python3-pip git wget

COPY requirements.txt requirements.txt

RUN pip install --upgrade pip setuptools wheel \
    && pip install -r requirements.txt

WORKDIR /app

RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz \
    && tar xzf boost_1_81_0.tar.gz -C . --strip-components=1 boost_1_81_0/boost

COPY . .

RUN make

ENV LC_ALL=C.utf8

ENTRYPOINT ["/app/.devops/tools.sh"]
