#include "minishell.h"

static int is_hidden(const char *filename)
{
    if (!filename)
        return 0;
    return (filename[0] == '.');
}

static void free_args(char **args)
{
    if (!args)
        return;
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

static int match_pattern(const char *filename, const char *pattern)
{
    if (*pattern == '\0')
        return (*filename == '\0');

    if (*pattern == '*')
    {

        while (*pattern == '*')
            pattern++;

        if (*pattern == '\0')
            return 1;

        int i = 0;
        while (filename[i])
        {
            if (match_pattern(&filename[i], pattern))
                return 1;
            i++;
        }

        return match_pattern("", pattern);
    }
    else
    {
        if (*filename == *pattern)
            return match_pattern(filename + 1, pattern + 1);
        return 0;
    }
}

static char **split_pattern_on_slash(const char *pattern)
{
    int seg_count = 1; 
    for (int i = 0; pattern[i]; i++)
    {
        if (pattern[i] == '/')
            seg_count++;
    }

    char **segs = (char **)malloc(sizeof(char *) * (seg_count + 1));
    if (!segs)
        return NULL;

    int len = (int)strlen(pattern);
    int start = 0;
    int idx = 0;
    for (int i = 0; i <= len; i++)
    {
        if (pattern[i] == '/' || pattern[i] == '\0')
        {
            int segment_len = i - start;
            char *segment = (char *)malloc(segment_len + 1);
            if (!segment)
            {

                for (int k = 0; k < idx; k++)
                    free(segs[k]);
                free(segs);
                return NULL;
            }

            for (int j = 0; j < segment_len; j++)
                segment[j] = pattern[start + j];
            segment[segment_len] = '\0';

            segs[idx++] = segment;
            start = i + 1; 
        }
    }
    segs[idx] = NULL;
    return segs;
}

static char *join_path(const char *dir, const char *name)
{
    if (!dir || !name)
        return NULL;

    int dir_len = (int)strlen(dir);
    int name_len = (int)strlen(name);
    int need_slash = 1;

    if (dir_len == 1 && dir[0] == '/')
        need_slash = 0;

    char *res = (char *)malloc(dir_len + name_len + (need_slash ? 1 : 0) + 1);
    if (!res)
        return NULL;

    int idx = 0;

    for (int i = 0; i < dir_len; i++)
        res[idx++] = dir[i];

    if (need_slash)
        res[idx++] = '/';

    for (int i = 0; i < name_len; i++)
        res[idx++] = name[i];

    res[idx] = '\0';
    return res;
}

static char **traverse_one_segment(const char *current_dir, const char *segment)
{
    DIR *d = opendir(current_dir);
    if (!d)
    {
        char **empty = (char **)malloc(sizeof(char*) * 1);
        if (empty)
            empty[0] = NULL;
        return empty; 
    }

    char **results = NULL;
    int count = 0;
    struct dirent *entry = NULL;

    while ((entry = readdir(d)) != NULL)
    {
        const char *filename = entry->d_name;
        int include_hidden = (segment && segment[0] == '.');

        if (!include_hidden && is_hidden(filename))
            continue;

        if (match_pattern(filename, segment))
        {
            char *fullpath = join_path(current_dir, filename);
            if (!fullpath)
                continue;

            char **tmp = (char **)malloc(sizeof(char *) * (count + 2));
            if (!tmp)
            {
                free(fullpath);
                continue;
            }

            for (int i = 0; i < count; i++)
                tmp[i] = results[i];

            tmp[count++] = fullpath;
            tmp[count] = NULL;

            free(results);
            results = tmp;
        }
    }
    closedir(d);

    if (!results)
    {
        results = (char **)malloc(sizeof(char*) * 1);
        if (results)
            results[0] = NULL;
    }
    return results;
}

static char **apply_pattern_segments(char **start_paths, char **segments)
{
    if (!start_paths || !segments)
        return NULL;

    char **current_list = start_paths;

    for (int i = 0; segments[i]; i++)
    {
        char **new_list = NULL;
        int new_count = 0;

        for (int pidx = 0; current_list[pidx]; pidx++)
        {

            if (strlen(segments[i]) == 0)
            {
                char **tmp = (char **)malloc(sizeof(char *) * (new_count + 2));
                if (!tmp)
                    continue;

                for (int k = 0; k < new_count; k++)
                    tmp[k] = new_list[k];

                int len = (int)strlen(current_list[pidx]);
                char *dup = (char *)malloc(len + 1);
                if (dup)
                {
                    for (int x = 0; x < len; x++)
                        dup[x] = current_list[pidx][x];
                    dup[len] = '\0';
                }

                tmp[new_count] = dup;
                tmp[new_count + 1] = NULL;

                free(new_list);
                new_list = tmp;
                new_count++;
            }
            else
            {

                char **matches = traverse_one_segment(current_list[pidx], segments[i]);

                int c = 0;
                while (matches && matches[c])
                    c++;

                for (int mm = 0; mm < c; mm++)
                {
                    char **tmp = (char **)malloc(sizeof(char *) * (new_count + 2));
                    if (!tmp)
                    {

                        free(matches[mm]);
                        continue;
                    }

                    for (int nn = 0; nn < new_count; nn++)
                        tmp[nn] = new_list[nn];

                    tmp[new_count] = matches[mm];
                    tmp[new_count + 1] = NULL;

                    free(new_list);
                    new_list = tmp;
                    new_count++;
                }

                if (matches)
                {

                    for (int k = c; matches[k]; k++)
                        free(matches[k]);
                    free(matches);
                }
            }
        }

        {
            int z = 0;
            while (current_list[z])
            {
                free(current_list[z]);
                z++;
            }
            free(current_list);
        }
        current_list = new_list;
    }
    return current_list;
}

static char **expand_path_pattern(const char *pattern)
{

    char **segs = split_pattern_on_slash(pattern);
    if (!segs)
    {
        char **empty = (char **)malloc(sizeof(char*) * 1);
        if (empty)
            empty[0] = NULL;
        return empty;
    }

    int is_absolute = (pattern[0] == '/');
    char **start = NULL;

    if (is_absolute)
    {
        start = (char **)malloc(sizeof(char*) * 2);
        if (!start)
        {
            free_args(segs);
            return NULL;
        }
        start[0] = strdup("/"); 
        start[1] = NULL;
    }
    else
    {
        start = (char **)malloc(sizeof(char*) * 2);
        if (!start)
        {
            free_args(segs);
            return NULL;
        }
        start[0] = strdup(".");
        start[1] = NULL;
    }

    char **res = apply_pattern_segments(start, segs);
    free_args(segs);

    if (!res)
        return NULL;

    if (!is_absolute)
    {
        for (int i = 0; res[i]; i++)
        {
            if (res[i][0] == '.' && res[i][1] == '/')
            {
                int len = (int)strlen(res[i]);

                for (int x = 0; x < len - 1; x++)
                    res[i][x] = res[i][x + 2];
                res[i][len - 2] = '\0';
            }
            if (res[i][0] == '\0')
            {

                free(res[i]);
                res[i] = strdup(".");
            }
        }
    }
    return res;
}

char **expand_wildcards(const char *token)
{
    if (!token)
        return NULL;

    int has_star = 0;
    for (int i = 0; token[i]; i++)
    {
        if (token[i] == '*')
        {
            has_star = 1;
            break;
        }
    }

    if (!has_star)
    {

        char **single = (char **)malloc(sizeof(char*) * 2);
        if (!single)
            return NULL;
        single[0] = strdup(token);
        single[1] = NULL;
        return single;
    }

    char **expanded = expand_path_pattern(token);
    if (!expanded)
    {

        char **res = (char **)malloc(sizeof(char*) * 2);
        if (!res)
            return NULL;
        res[0] = strdup(token);
        res[1] = NULL;
        return res;
    }

    if (!expanded[0])
    {
        free_args(expanded);
        char **res = (char **)malloc(sizeof(char*) * 2);
        if (!res)
            return NULL;
        res[0] = strdup(token);
        res[1] = NULL;
        return res;
    }

    return expanded;
}