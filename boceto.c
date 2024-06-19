


typedef struct s_process
{
	char **args;
	int	pid;
	char **env;
	int std_in;
	int std_out;
} t_process;

t_process *init_commands(...)
{
	// malloc(...)

	while ()
	{
		// args
		// env
	}
}

void init_pipes(t_process *childs)
{
	int pipe_[2];

	while ()
	{
		pipe(pipe_)
		this_proc->std_out = pipe_[1];
		next_proc->std_in = pipe_[0];
	}
}

void exc_childs(t_process *childs)
{
	int pid;
	while()
	{
		pid = fork()
		{
			//hijo
			// dup
			// cerrar los pipes que no usas (while que cierra todos los pipes menos los propios)
			// execve(...)
		}
		{
			// padre
			child->pid = pid;
		}
	}
	// El padre cierra TODOS los pipes
}


int wait_childs(t_process * childs)
{
	int status;

	while ()
	{
		waitpid(child->pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

int main()
{
	t_process *childs;

	childs = init_commands(argv...);
	init_pipes(childs);
	exec_childs(childs);
	return (wait_childs(childs));
}