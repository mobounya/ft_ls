/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:06:15 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/09 19:48:53 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*ft_read_file(char *filename, t_width *max)
{
	t_file			*file;
	struct stat		file_info;

	if (filename == NULL || !(file = ft_memalloc(sizeof(t_file))))
		return (NULL);
	errno = 0;
	file->minor = -1;
	file->major = -1;
	file->path = ft_get_path(filename);
	file->stat = NULL;
	if (lstat(file->path, &file_info) == -1)
	{
		if (errno == EACCES)
			file->error = ft_strdup(strerror(errno));
		else
			ft_sort_errors(ft_strdup(strerror(errno)), filename, max, &file);
		return (file);
	}
	ft_get_xattr(file->path, file);
	file->stat = ft_getstat(file_info);
	if (S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode))
		ft_set_mj_mn(file, file_info);
	if (ft_check_bit(max->flag, COLOR_BIT))
		file->color = ft_get_color(file->stat->st_mode);
	return (file);
}

int		ft_read_dir(t_file **node, char *dirpath, int *flag, int sort_option)
{
	char			*entrypath;
	t_file			*dir_node;
	DIR				*stream;
	struct dirent	*entry;
	t_width			*max;

	errno = 0;
	stream = opendir(dirpath);
	if (stream == NULL || !(max = ft_memalloc(sizeof(t_width))))
		return (errno);
	max->minor = -1;
	max->major = -1;
	max->flag = *flag;
	while ((entry = readdir(stream)))
	{
		entrypath = ft_strjoin(dirpath, entry->d_name);
		if (!(dir_node = ft_get_data(&entrypath, flag, entry->d_name, max)))
			continue ;
		ft_insert_data(node, dir_node, ft_compare, sort_option);
	}
	ft_strdel(&entrypath);
	(*node) ? ((*node)->max = max) : free(max);
	closedir(stream);
	return (0);
}

t_file	*ft_read(char *filename, int option, int *flag, t_width *max)
{
	t_file			*node;
	char			*path;
	char			*dirpath;
	int				errno;

	if (!(node = ft_read_file(filename, max)))
		return (NULL);
	node->filename = ft_strdup(filename);
	if (node->error)
		ft_sort_errors(ft_strdup(strerror(errno)), filename, max, &node);
	if (node && node->stat && !S_ISDIR(node->stat->st_mode) && max)
		ft_get_max(max, node);
	if (node && node->stat && S_ISDIR(node->stat->st_mode))
	{
		if (max)
			max->dirs_count++;
		dirpath = ft_get_path(filename);
		path = ft_strjoin(dirpath, "/");
		free(dirpath);
		if ((errno = ft_read_dir(&(node)->dir_files, path, flag, option)) != 0)
			node->error = ft_strdup(strerror(errno));
		free(path);
	}
	return (node);
}

int		ft_parse_flags(char **argv, uint *i, int *flag)
{
	while (argv[*i] && argv[*i][0] == '-')
	{
		if (ft_strequ(argv[*i], "--"))
		{
			*i = *i + 1;
			break ;
		}
		if (!ft_set_flags(flag, argv[*i]))
			exit(0);
		*i = *i + 1;
	}
	return (*i);
}

int		ft_parse_argv(char **argv, int *flag, t_file **root, int *sort_option)
{
	uint			i;
	t_file			*node;
	t_width			*max;
	uint			temp;

	if (!(max = ft_memalloc(sizeof(t_width))))
		return (-1);
	max->minor = -1;
	max->major = -1;
	i = 1;
	temp = ft_parse_flags(argv, &i, flag);
	ft_set_option(flag, sort_option);
	max->flag = *flag;
	while (argv[i])
	{
		if ((node = ft_read(argv[i], *sort_option, flag, max)) == NULL && i++)
			continue;
		ft_insert_data(root, node, ft_compare, *sort_option);
		i++;
	}
	ft_print_errors(&max->errors);
	(*root) ? (*root)->max = max : free(max);
	if (i > temp && *root == NULL)
		exit(1);
	return (1);
}
