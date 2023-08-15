FROM ubuntu:20.04

RUN apt-get update
RUN apt-get install gcc make libncurses5-dev libncursesw5-dev -y

WORKDIR /app

COPY ./data ./data
COPY ./src ./src
COPY ./Makefile .

RUN make

CMD ["./rts-game"]
