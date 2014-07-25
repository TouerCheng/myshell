myshell: explian_input.o find_command.o do_cmd.o git_input.o print_prompt.o main.o
	gcc -o myshell explian_input.o find_command.o do_cmd.o git_input.o print_prompt.o main.o
	make clean
explian_input.o:
find_command.o:
do_cmd.o:
git_input.o:
print_prompt.o:
main.o:
.PHONY:clean
clean:
		rm -f *.o
