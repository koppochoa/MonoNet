FROM ubuntu:24.04

RUN apt update && \
    apt install -y \
        build-essential \
        gdb \
        valgrind \
        man-db \
        libssl-dev \
&& rm -rf /var/lib/apt/lists/*
WORKDIR /app

CMD ["bash"]
