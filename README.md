# Common Hardware Library

This library was created as a way for me to create and store many hardware modules that I find myself re-implementing across different projects. The idea is to make the process of getting started with creation and simulation of system verilog modules as quick as possible. To this end, I have created a project template and python script to quickly spin up new projects targeting [Verilator](https://www.veripool.org/verilator/) as the simulator. Verilator was chosen because it is FOSS.

## New Module Creation
In order to create a new module project folder you simply need to run:
```shell
python create_from_template <module_name> <template_dir>
```
where,<br>
module_name: Required! = Your intended Verilog module name you wish to create<br>
template_dir: Optional = Path to template directory if using other than the default './template'

## Docker
I use docker to compile and run verilated simiulations as it provides a consistent and clean environment to run in. I have included the Dockerfile needed to create a container with verilator installed. To build the image for the first time run the following from the repo's root directory:
```shell
cd docker
make build
```
Once built, the container can be run with:
```shell
make run
```
By default this will mount the repo's root director into /root in the container so that changes made in this directory will be saved.

## Using Verilator
Once running in the docker container you simply change directory into whichever module you want to test and from there the makefile will perform most desired actions.

#### Simulate
In order to perform a simulation of the module and generate waveforms:
```shell
make
```

#### Build
In order to just build but not run the simulation:
```shell
make build
```

#### Lint
To only lint your .sv module:
```shell
make lint
```

## License
Distributed under the MIT License. See `LICENSE` for more information.