import argparse
import logging
import os

from jinja2 import Environment, FileSystemLoader
from jinja2 import exceptions as jinja_exceptions

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument("module_name", help="Name of the SV module to create a Verilator project folder for")
    parser.add_argument("--temp-dir", default="template", help="Directory to get template project files from", required=False)

    args = parser.parse_args()

    logging.info("Creating New Project '%s' From Template Directory '%s'", args.module_name, args.temp_dir)

    proj_path = os.path.join(os.getcwd(), f"modules/{args.module_name}")
    hvl_path = os.path.join(proj_path, "hvl")
    rtl_path = os.path.join(proj_path, "rtl")
    template_path = os.path.join(os.getcwd(), args.temp_dir)

    # Create Project Folder Structure
    if not os.path.exists(proj_path):
        os.mkdir(proj_path)
    if not os.path.exists(hvl_path):
        os.mkdir(hvl_path)
    if not os.path.exists(rtl_path):
        os.mkdir(rtl_path)

    # Load Templates
    try:
        environment = Environment(loader=FileSystemLoader(args.temp_dir))
        tb_template = environment.get_template("/hvl/top_tb.cpp")
        rtl_template = environment.get_template("/rtl/template_mod.sv")
        make_template = environment.get_template("/Makefile")
    except jinja_exceptions.TemplateNotFound:
        print("Template folder not found, or structure corrupted! exiting...")
        exit(1)

    # Render Templates Using Project Name
    tb_content = tb_template.render(mod_name = args.module_name)
    rtl_content = rtl_template.render(mod_name = args.module_name)
    make_content = make_template.render(mod_name = args.module_name)

    # Write Rendered Templates to Project Directory
    with open(os.path.join(hvl_path, f"{args.module_name}_tb.cpp"), mode="w", encoding="utf-8") as top_tb:
        top_tb.write(tb_content)

    with open(os.path.join(proj_path, "Makefile"), mode="w", encoding="utf-8") as make:
        make.write(make_content)

    with open(os.path.join(rtl_path, f"{args.module_name}.sv"), mode="w", encoding="utf-8") as rtl:
        rtl.write(rtl_content)

    # Things To Copy Over Untemplated
    extras = [
        (os.path.join(template_path, "hvl/utils.h"), os.path.join(hvl_path, "utils.h"))
    ]

    for src, dst in extras:
        os.popen(f"cp {src} {dst}")