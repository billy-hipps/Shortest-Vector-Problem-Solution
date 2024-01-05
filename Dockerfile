FROM ubuntu:latest
LABEL maintainer="billy hipps <billyhipperson@hotmail.co.uk>" \
        description="Cool"
RUN mkdir /code 

COPY code /code
RUN apt-get update && apt-get install -y \
    make \
    gcc \
    gdb \
    bash \
    valgrind\
    && rm -rf /var/lib/apt/lists/*
WORKDIR /code
ENTRYPOINT ["bash"]