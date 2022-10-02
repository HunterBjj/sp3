FROM ubuntu
COPY main.cpp main.cpp
RUN apt-get update -y
RUN apt-get install -y g++
RUN gcc main.cpp -o main -g -lstdc++
CMD ./main