#!/usr/bin/env python3

import os, sys
import cd, exit

def execute(args):
  if len(args) > 1 and args[-2] == '>':
    output_file = args[-1]
    args = args[:-2]
    file_descriptor = open(output_file, "w")
    os.dup2(file_descriptor.fileno(), sys.stdout.fileno())

  os.execvp(args[0], args)

def main():
  while True:
    line = input('dtshell$ ')
    args = line.split(' ')

    if args[0] == "cd":
      cd.cd(args)

    elif args[0] == "exit":
      exit.exit()

    else:
      pid = os.fork()

      if pid == 0:
        execute(args)

      else:
        os.wait()

if __name__ == "__main__":
  main()
