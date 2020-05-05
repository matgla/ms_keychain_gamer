#!/usr/bin/python3

import argparse
import sys
from PIL import Image

parser = argparse.ArgumentParser(description = "Sprite generator, converts image to source file")
parser.add_argument("-o", "--output", dest="output_file", action="store", help="Path to output file", required=True)
parser.add_argument("-i", "--file", dest="input_file", action="store", help="Path to input file, for animation format is, file1,file2,file3", required=True)
parser.add_argument("-n", "--namespace", dest="namespace", action="store", default="", help="Namespace for image")
parser.add_argument("-s", "--sprite_name", dest="sprite_name", action="store", help="Name for sprite", required=True)
args, rest = parser.parse_known_args()

def get_image_size(files):
    x_min = sys.maxsize
    x_max = 0
    y_min = sys.maxsize
    y_max = 0
    for file in files.split(","):
        img = Image.open(args.input_file)
        x_start, y_start, x_stop, y_stop = img.getbbox()
        if x_start < x_min:
            x_min = x_start
        if x_stop > x_max:
            x_max = x_stop
        if y_start < y_min:
            y_min = y_start
        if y_stop > y_max:
            y_max = y_stop

    return (x_min, y_min, x_max, y_max)

def main():
    print("Converting image from:", args.input_file, ", to:", args.output_file)
    with open(args.output_file, "w") as output:
        output.write("// This file was generated automatically \n\n")
        output.write("// This file is part of MS keychain gamer project. \n")
        output.write("// Copyright (C) 2020 Mateusz Stadnik*/\n")
        output.write("//\n")
        output.write("// This program is free software: you can redistribute it and/or modify\n")
        output.write("// it under the terms of the GNU General Public License as published by\n")
        output.write("// the Free Software Foundation, either version 3 of the License, or\n")
        output.write("// (at your option) any later version.\n")
        output.write("//\n")
        output.write("// This program is distributed in the hope that it will be useful,\n")
        output.write("// but WITHOUT ANY WARRANTY; without even the implied warranty of\n")
        output.write("// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n")
        output.write("// GNU General Public License for more details.\n")
        output.write("//\n")
        output.write("// You should have received a copy of the GNU General Public License\n")
        output.write("// along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\n")
        output.write("#pragma once\n\n")
        output.write("#include <msgui/Factory.hpp>\n\n")
        for namespace in args.namespace.split("::"):
            output.write("namespace " + namespace + "\n")
            output.write("{\n")

        x_min, y_min, x_max, y_max = get_image_size(args.input_file)
        x_size = x_max - x_min
        y_size = y_max - y_min

        output.write("constexpr static auto " + args.sprite_name + " = msgui::factory::make_bitmap<" + str(x_size) + ", " + str(y_size) + ">(\n")

        for file in args.input_file.split(","):
            img = Image.open(args.input_file)
            x_start = x_min
            x_stop = x_max
            y_start = y_min
            y_stop = y_max

            for y in range(y_start, y_stop):
                output.write("    ")
                for x in range(x_start, x_stop):
                    _, _, _, is_set = img.getpixel((x, y))
                    if is_set:
                        last = x == x_stop - 1 and y == y_stop - 1
                        if last:
                            output.write("1")
                        else:
                            output.write("1,")
                    else:
                        last = x == x_stop - 1 and y == y_stop -1
                        if last:
                            output.write("0")
                        else:
                            output.write("0,")
                output.write("\n")
            output.write(");\n\n")
        for namespace in args.namespace.split("::"):
            output.write("} // " + namespace + "\n")


main()
