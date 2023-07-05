
#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

#include "includes/fdf.h"

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

unsigned int	ft_get_ticks(void)
{
	struct timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	return ((now.tv_sec * 1000) + (now.tv_nsec / 1000000));
}


int	init_game_vars(t_game *game)
{
	game->rays = ft_calloc(sizeof(t_raycast), 1);
	if (game->rays == NULL)
		return (0);
	game->mlx = mlx_init();
	game->rays->mlx = game->mlx;
	game->screen_width = 640;
	game->screen_height = 480;
	game->tex_width = 64;
	game->tex_height = 64;
	game->win = mlx_new_window(game->mlx, game->screen_width, \
									game->screen_height, "Game");
	game->rays->win = game->win;
	game->texture = (uint32_t **) ft_calloc(sizeof(uint32_t *), 4);
	if (game->texture == NULL)
		return (0);
	return (1);
}

int main(int /*argc*/, char argv[])
{

	t_game	*game;

	(void)argv;
	game = ft_calloc(sizeof(t_game), 1);
	init_game_vars(game);
	t_raycast	*rays;

	mlx_clear_window(game->mlx, game->win);
	game->rays->time = ft_get_ticks();
	rays = game->rays;
	rays->img = mlx_new_image(game->mlx, game->screen_width, \
													game->screen_height);
	rays->img_addr = mlx_get_data_addr(rays->img, &rays->bits_per_pixel, \
	&rays->line_length, &rays->endian);
	
	mlx_hook(game->win, 2, 1L << 0, keys, game);
	floor_ceiling(game);
	wall_casting(game);
	mlx_put_image_to_window(game->mlx, game->win, rays->img, 0, 0);
	rays->pos_x = 22.0;
	rays->pos_y = 11.5;
	rays->dir_x = -1.0;
	rays->dir_y = 0.0;
	rays->plane_x = 0.0;
	rays->plane_y = 0.66;
	int	buffer[screenHeight][screenWidth]; // y-coordinate first because it works per scanline
	int	texture[8][texWidth * texHeight];
	for(int x = 0; x < texWidth; x++)
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	 while(!done())
  	{
		for(int x = 0; x < screenWidth; x++)
		{
		//calculate ray position and direction
		rays->camera_x = 2*x/screenWidth - 1; //add double
		rays->ray_dir_x = rays->dir_x + rays->plane_x * rays->camera_x;
		rays->ray_dir_y  = rays->dir_y + rays->plane_y * rays->camera_x;

		//which box of the map we're in
		rays->map_x = floor(rays->pos_x);
		rays->map_y = floor(rays->pos_y);

		//length of ray from one x or y-side to next x or y-side

		rays->delta_dist_x = sqrt(1 + ( rays->ray_dir_y *  rays->ray_dir_y) / (rays->ray_dir_x  * rays->ray_dir_x));
		rays->delta_dist_y = sqrt(1 + (rays->ray_dir_x * rays->ray_dir_x) / (rays->ray_dir_y * rays->ray_dir_y));

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		rays->hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rays->ray_dir_x < 0)
		{
			stepX = -1;
			rays->side_dist_x = (rays->pos_x - rays->map_x) * rays->delta_dist_x;
		}
		else
		{
			stepX = 1;
			rays->side_dist_x = (rays->map_x + 1.0 - rays->pos_x) * rays->delta_dist_x;
		}
		if (rays->ray_dir_y < 0)
		{
			stepY = -1;
			rays->side_dist_y = (rays->pos_y - rays->map_y) * rays->delta_dist_y;
		}
		else
		{
			stepY = 1;
			rays->side_dist_y = (rays->map_y + 1.0 - rays->pos_y) * rays->delta_dist_y;
		}
		 while (rays->hit == 0)
      	{
        //jump to next map square, either in x-direction, or in y-direction
			if (rays->side_dist_x < rays->side_dist_y)
			{
				rays->side_dist_x  += rays->delta_dist_x;
				rays->map_x  += rays->step_x;
				rays->side = 0;
			}
			else
			{
				rays->side_dist_y  += rays->delta_dist_y;
				rays->map_y += rays->step_y;
				rays->side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[rays->map_x][rays->map_y] > 0)
				rays->hit = 1;
      	}


		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if(side == 0) rays->perp_wall_dist = (rays->side_dist_x - rays->delta_dist_x);
		else          rays->perp_wall_dist = (rays->side_dist_y - rays->delta_dist_y);

		//Calculate height of line to draw on screen
		rays->line_height = (int) (mapHeight / rays->perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		rays->draw_start = -rays->line_height / 2 + mapHeight / 2;
		if(rays->draw_start < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h) drawEnd = h - 1;
	}
}

