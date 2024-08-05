FROM ubuntu:latest
LABEL maintainer="username <email adress>" \
        description="Cool"
RUN mkdir /code 

COPY code /code
RUN apt-get update && apt-get install -y \
    make \
    gcc \
    gdb \
    bash \
    valgrind \
    bc \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /code
ENTRYPOINT ["bash"]