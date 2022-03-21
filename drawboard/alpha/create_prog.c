#include "mlx.h"
#include "prog.h"
#include <unistd.h>
#include <stdlib.h>

typedef struct s_el
{
	int	win_size;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*pxl;
	char	***m;
	int	bpp;
	int	sl;
	int	end;
	int	x_inc;
	int	y_inc;
	int	i;
}	t_el;

char	***creatematrix(char *img, int img_size, int img_sl)
{
	int		i;
	char	*ptr;
	char	**pptr;
	char	***ppptr;

	ptr = img;
	pptr = malloc(sizeof(char *) * img_size * img_size);
	i = 0;
	while (ptr < (img + img_size * img_sl))
	{
		pptr[i++] = ptr;
		ptr = ptr + 4;
	}
	i = 0;
	ppptr = malloc(img_size * sizeof(char **));
	while (i < img_size - 1)
	{
		ppptr[i++] = pptr;
		pptr = pptr + img_size;
	}
	return (ppptr);
}

int color_pxl(t_el *el, int x, int y, char color)
{
    if (color == 'b')
    {
	el->m[x][y][0] = 0;
	el->m[x][y][1] = 0;
	el->m[x][y][2] = 0;
    }
    else if (color == 'w')
    {	
	el->m[x][y][0] = 255;
	el->m[x][y][1] = 255;
	el->m[x][y][2] = 255;
    }

    return (0);
}


int put_whitebutton(t_el *el)
{
    int	size;
    int x;
    int	y;

    size = el->win_size / 10;
    x = 0;
    y = size;
    while (x < size)
    {
	color_pxl(el, x, y, 'b');
	x++;
    }
    printf("%d\n", y);
    while (y >= 0)
    {
	color_pxl(el, x, y, 'b');
	y--;
    }
    return (0);
}

int whiteitout(t_el *el)
{
    int	     ix;
    int	    iy;

    ix = 0;
    iy = 0;
    while (ix < el->win_size - 1) 
    {
	iy = 0;
	while (iy < el->win_size - 1)
	{
	    color_pxl(el, ix, iy, 'w');
	    iy++;
	}
	ix++;
    }
    put_whitebutton(el);
    return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
    t_el *el;

    if(param == NULL)
	return (1);
    el = (t_el *)param;
    if (button == 1)
    {
	if (x < 80 && y < 80)
	    whiteitout(el);
	el->i = el->i * -1;
    }
    if (el->i == -1)
    {
	el->x_inc = 0;
	el->y_inc = 0;
	return (0);
    }
    if (button == 5)
	el->y_inc = el->y_inc - 1;
    if (button == 6)
	el->x_inc = el->x_inc + 1;
    if (button == 4)
	el->y_inc = el->y_inc + 1;
    if (button == 7)
	el->x_inc = el->x_inc - 1;
    y = y + el->y_inc;
    x = x + el->x_inc;
    el->m[400][400][0] = 0;
    el->m[y][x][1] = 0;
    el->m[y][x][2] = 0;
    el->m[y][x][3] = 0;
    mlx_clear_window(el->mlx_ptr, el->win_ptr);
    mlx_put_image_to_window(el->mlx_ptr, el->win_ptr, el->img_ptr, 0, 0);
    printf("button: %d\nx: %d\ny: %d", button, x, y);
    printf("\nbpp:%d\n", el->end);
    return (0);
}

int create_prog()
{
	t_el	*el;

	el = malloc(sizeof(t_el));
	el->win_size = 800;
	el->mlx_ptr = mlx_init();
	el->win_ptr = mlx_new_window(el->mlx_ptr, el->win_size, el->win_size, "drawboard");
	el->img_ptr = mlx_new_image(el->mlx_ptr, el->win_size, el->win_size);
	el->pxl = mlx_get_data_addr(el->img_ptr, &(el->bpp), &(el->sl), &(el->end));
	el->m = creatematrix(el->pxl, el->win_size, el->sl);
	el->i = -1;
	el->x_inc = 0;
	el->y_inc = 0;

	whiteitout(el);
	put_whitebutton(el);
	int i;
	i = mlx_put_image_to_window(el->mlx_ptr, el->win_ptr, el->img_ptr, 0, 0);
	printf("mputimtowin1: %d\n", i);
	mlx_mouse_hook(el->win_ptr, mouse_hook, (void *)el);
	mlx_loop(el->mlx_ptr);
	
	return(0);
}


