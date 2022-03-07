#include "mlx.h"
#include "prog.h"
#include <unistd.h>
#include <stdlib.h>

typedef struct s_el
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*pxl;
	char	***m;
	int	bpp;
	int	sl;
	int	end;
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
	i = img_size - 1;
	while (i >= 0)
	{
		ppptr[i--] = pptr;
		pptr = pptr + img_size;
	}
	return (ppptr);
}

int mouse_hook(int button, int x, int y, void *param)
{
    t_el *el;

    if(param == NULL)
	return (1);
    el = (t_el *)param; 
    el->m[400][400][0] = 0;
    el->m[400][400][1] = 0;
    el->m[400][400][2] = 0;
    el->m[400][400][3] = 0;
    mlx_mouse_hookq
    printf("button: %d\nx: %d\ny: %d", button, x, y);
    printf("\nbpp:%d\n", el->end);
    return (0);
}

int create_prog()
{
	int	win_size;
	t_el	*el;

	el = malloc(sizeof(t_el));
	win_size = 800;
	el->mlx_ptr = mlx_init();
	el->win_ptr = mlx_new_window(el->mlx_ptr, win_size, win_size, "drawboard");
	el->img_ptr = mlx_new_image(el->mlx_ptr, win_size, win_size);
	el->pxl = mlx_get_data_addr(el->img_ptr, &(el->bpp), &(el->sl), &(el->end));
	el->m = creatematrix(el->pxl, win_size, el->sl);
	size_t i;
	
	i = 0;
	while (i < ((size_t)(win_size) * el->sl))
	{
		if ((i + 1) % 4)
			*((el->pxl) + i) = 255;
		i++;
	}	
	mlx_put_image_to_window(el->mlx_ptr, el->win_ptr, el->img_ptr, 0, 0);
	mlx_mouse_hook(el->win_ptr, mouse_hook, (void *)el);
	mlx_loop(el->mlx_ptr);
	
	return(0);
}


