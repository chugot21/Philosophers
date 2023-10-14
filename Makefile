# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clara <clara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/10/11 13:03:46 by chugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo

SRCS =	philo.c \
		threads.c \
		routine.c \
		check_death.c \
		ft_utils.c \

CC = cc

FLAGS = -g3 -pthread -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC)  $(FLAGS) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:
		rm -f $(OBJS) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
