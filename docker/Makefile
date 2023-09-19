.PHONY: run
run:
	sudo docker run -it --rm -v $(PWD)/../:/root verilator:latest

build: ./Dockerfile
	sudo docker build -t verilator .
