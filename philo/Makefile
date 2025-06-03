# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 19:17:04 by meandrad          #+#    #+#              #
#    Updated: 2025/06/03 18:35:40 by meandrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = cc -Wall -Wextra -Werror -g -lpthread

SRCS = \
		philo.c \
		

OBJS = $(SRC: .c=.o)

all: $(NAME)

$(NAME) = $(OBJS)
	$(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean clean

.PHONY: all clean fclean re