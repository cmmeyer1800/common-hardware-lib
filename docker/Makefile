.PHONY: run
run:
	docker run -it --rm -v $(PWD)/../:/root verilator:latest

build: ./Dockerfile
	docker build -t verilator .