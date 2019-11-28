/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:02:15 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/08 02:50:09 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_get_max(t_width *max, t_file *node)
{
	uint	uname_len;
	uint	gname_len;

	(S_ISDIR(node->stat->st_mode)) ? max->dirs_count++ : max->files_count++;
	uname_len = ft_strlen(node->stat->uname);
	gname_len = ft_strlen(node->stat->gname);
	max->st_stat = 1;
	if (node->stat->nlink > max->mx_links)
		max->mx_links = node->stat->nlink;
	if (node->stat->size > max->mx_size)
		max->mx_size = node->stat->size;
	if (uname_len > max->mx_uname)
		max->mx_uname = uname_len;
	if (gname_len > max->mx_gname)
		max->mx_gname = gname_len;
	if (node->acl)
		max->acl = node->acl;
	if (node->size)
		max->size = node->size;
	if (node->minor > max->minor)
		max->minor = node->minor;
	if (node->major > max->major)
		max->major = node->major;
	max->st_blocks += node->stat->st_blocks;
}

t_stat	*ft_getstat(struct stat file_info)
{
	struct passwd	*owner;
	struct group	*grp;
	t_stat			*newstat;

	if ((newstat = ft_memalloc(sizeof(t_stat))) == NULL)
		return (NULL);
	owner = getpwuid(file_info.st_uid);
	grp = getgrgid(file_info.st_gid);
	newstat->uname = ft_strdup(owner->pw_name);
	newstat->gname = ft_strdup(grp->gr_name);
	newstat->st_mode = file_info.st_mode;
	newstat->atime = file_info.st_atimespec.tv_sec;
	newstat->gid = file_info.st_gid;
	newstat->uid = file_info.st_uid;
	newstat->nlink = file_info.st_nlink;
	newstat->modtime = file_info.st_mtimespec.tv_sec;
	newstat->size = file_info.st_size;
	newstat->st_blocks = file_info.st_blocks;
	return (newstat);
}

t_file	*ft_get_data(char **entrypath, int *flag, char *d_name, t_width *max)
{
	t_file			*dir_node;

	dir_node = NULL;
	if (!(ft_check_bit(*flag, ALL_BIT)) && d_name[0] == '.')
		ft_strdel(entrypath);
	if (*entrypath)
	{
		if (!(dir_node = ft_read_file(*entrypath, max)))
		{
			ft_strdel(entrypath);
			return (NULL);
		}
		free(dir_node->filename);
		if (dir_node->stat != NULL)
			ft_get_max(max, dir_node);
		else
			max->st_stat = 0;
		dir_node->filename = ft_strdup(d_name);
		ft_strdel(entrypath);
	}
	return (dir_node);
}

void	ft_get_xattr(const char *pathname, t_file *node)
{
	acl_entry_t		entry_p;
	acl_t			acl;
	ssize_t			size;

	entry_p = NULL;
	acl = acl_get_link_np(pathname, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry_p) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	size = listxattr(pathname, NULL, 0, XATTR_NOFOLLOW);
	if (size <= 0)
		node->size = 0;
	if (size > 0)
	{
		node->size = size;
		acl_free(acl);
	}
	else if (acl != NULL)
		node->acl = acl;
}

void	ft_get_time(time_t c_time, time_t modtime)
{
	char		*get_time;

	get_time = ctime(&modtime);
	if (c_time - modtime >= 15778476 || modtime - c_time >= 15778476)
	{
		ft_putstr("  ");
		get_time[24] = '\0';
		ft_putstr(get_time + 20);
	}
	else
	{
		ft_putstr(" ");
		get_time[16] = '\0';
		ft_putstr(get_time + 11);
	}
	ft_putchar(' ');
}
