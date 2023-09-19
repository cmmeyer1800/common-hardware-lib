.PHONY: run
run:
	docker run -it --rm -v $(PWD)/../:/root verilator:latest

build: ./Dockerfile
	docker build -t verilator .

build/test: ./Dockerfile
	docker build -t verilator-testing test.Dockerfile