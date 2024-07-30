 #include <stdio.h>
#include <stdbool.h>

int isPerimeterSurroundedBy(int **map, int rows, int *cols)
{
    int j;
	int i;
	j = 0;
    while (j < cols[0])
	{
        if (map[0][j] != 1)
            return (1);
		j++;
	}
	j = 0;
    while (j < cols[rows - 1] )
	{
        if (map[rows - 1][j] != 1)
            return (1);
		j++;
    }
	i = 0;
    while (i < rows ) 
	{
        if (map[i][0] != 1)
        		return (1);
			i++;
        if (cols[i] > 0 && map[i][cols[i] - 1] != 1)
            return (1); 
    }
    return (0);
}
