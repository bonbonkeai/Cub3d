Parsing

To do list:

main function :		int parse_file(const char *filepath, t_game *game)
					int parse_config(char *line, t_parse *parser);

config function :	int parse_texture(...)
					int is_texture(...) NO, SO, WE, EA

					NO ./textures/north.xpm
					SO ./textures/south.xpm
					WE ./textures/west.xpm
					EA ./textures/east.xpm
					F RGB Color
					C Ceilling color

parse validation : 	int map_closed_valid(?)
					int player_valid(?)
					int char_valid(?)

					Check if the map is closed (walls)
					Check if we only have one player
					Check if all the line is valid (char, int, whitespaces, etc...)

error			 :	ft_error(char *str, char *arg)

					print the error

utils			 :	use trim and check empty line