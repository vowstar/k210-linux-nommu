void _entry(int argc, char *argv[]);

void _entry(int argc, char *argv[])
{
    extern int main(int argc, char *argv[]);
    extern long syscall(long id, ...);
    main(argc, argv);
    syscall(94, 42);
}
