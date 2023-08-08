static int generate_random_number() {
    static int rand_num = 0;
    return rand_num++;
}

static char *generate_unique_filename() {
    char *tty_name = ttyname(1);
    char *tty_num = ft_strchr(tty_name, '0');
    int rand_num = generate_random_number();
    
    char *filename = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(rand_num));
    char *unique_filename = ft_strjoin(filename, tty_num);
    
    return unique_filename;
}

int create_herdoc_file(char *name) {
    name = generate_unique_filename();
	printf("name : %s\n", name);
    int fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
    return fd;
}

int	ft_herdoc(t_stack *list, int flag, t_envir *envr)
{
	int			fd;
	static int	rand;
	char		*her;
	char		*name;
	char		*tty;


	fd = create_herdoc_file(name);
	if (list->next && (!ft_strcmp(list->next->word, "\"\"")
			|| !ft_strcmp(list->next->word, "\'\'")))
	{
		free(list->next->word);
		list->next->word = ft_strdup("");
	}
	signal(SIGINT, ft_herd);
	tty = dell_qots(list->next->word);
	free(list->next->word);
	list->next->word = tty;
	while (isatty(STDIN_FILENO))
	{
		her = readline("> ");
		if (!her)
		{
			break ;
		}
		if (!ft_strlen(her) && !list->next)
			break ;
		else if (list->next)
		{
			return_space_to_real_value(list->next->word);
			if (!ft_strcmp(her, list->next->word))
			{
				free(her);
				break ;
			}
		}
		if (g_flags.delim_flags == 0)
			her = ft_add_variables(her, envr, 1);
		ft_putstr_fd(her, fd);
		ft_putstr_fd("\n", fd);
		free(her);
	}
	if (g_flags.delim_flags != 0)
		g_flags.delim_flags--;
	signal(SIGINT, ft_sigint);
	if (!isatty(STDIN_FILENO))
		return (free(her), free(name), fd_herdoc(&fd), -5);
	free(list->word);
	list->word = ft_strdup("");
	if (list->next && list->next->next)
	{
		list->word = list->next->next->word;
		list->key = COMMAND;
		list->next->next->word = ft_strdup("");
	}
	if (list->next)
	{
		free(list->next->word);
		list->next->word = ft_strdup(name);
		list->next->key = FILE_IN;
	}
	free(name);
	return (fd);
}
