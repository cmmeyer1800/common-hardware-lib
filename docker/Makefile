.PHONY: build run

build:
	docker build -t verilator .

run:
	docker run -it --rm -v $(PWD)/../:/root verilator:latest