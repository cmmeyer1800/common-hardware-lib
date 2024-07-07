.PHONY: run
run:
	docker run -it --entrypoint /bin/bash --rm -v $(PWD)/../:/root verilator:latest

build: ./Dockerfile
	docker build -t verilator .

.PHONY: test
test:
	docker run -t --rm -v $(PWD)/../:/root --entrypoint /root/scripts/test verilator:latest