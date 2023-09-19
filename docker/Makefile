.PHONY: run
run:
	sudo docker run -it --rm -v $(PWD)/../:/root verilator:latest

build: ./Dockerfile
	sudo docker build -t verilator .

build/test: ./Dockerfile
	sudo docker build -t verilator-testing test.Dockerfile