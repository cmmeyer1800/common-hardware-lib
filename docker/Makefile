.PHONY: run
run:
	docker run -it --rm -v $(PWD)/../:/root verilator:latest

build: ./Dockerfile
	docker build -t verilator .

.PHONY: test
test:
	docker run -it --rm -v $(PWD)/../:/root --entrypoint /root/scripts/test verilator:latest