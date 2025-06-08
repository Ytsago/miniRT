void	jump_spaces(char **str)

{
	while (**str == ' ')
		++(*str);
}

void	jump_zeros(char **str)

{
	while (**str == '0')
		++(*str);
}
