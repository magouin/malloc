# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magouin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/27 13:24:03 by magouin           #+#    #+#              #
#    Updated: 2017/11/30 16:50:35 by magouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	= libft_malloc_$(HOSTTYPE).so
CC		= gcc
WFLAGS	= -Wall -Wextra -Werror -g
OPTI	= -I

LS		= ls -1
GREP	= grep
MKDIR	= mkdir -p
RM		= rm -rf

DSRC		= src
DLIB		= libft
DINC		= inc
DINCLIB		= inc \
		  		  $(DLIB)/inc
DOBJ	= obj

FSRC		:= $(shell $(LS) $(DSRC) | $(GREP) \.c$)
FOBJ		:= $(FSRC:.c=.o)
LIBFT		:= libft.a

FSRC		:= $(addprefix $(DSRC)/, $(FSRC))
FOBJ		:= $(addprefix $(DOBJ)/, $(FOBJ))
FINCLIB		:= $(addprefix $(OPTI) , $(DINCLIB))
LIBFT		:= $(addprefix $(DLIB)/, $(LIBFT))
INC 		= $(addprefix -I,$(DINC))

all: libft $(FOBJ) $(NAME)
		@rm libft_malloc.so 2> /dev/null || true
		ln -s $(NAME) libft_malloc.so
		gcc main.c libft_malloc.so libft/libft.a -g

$(NAME): $(LIBFT) $(FOBJ)
		gcc -shared -o $@ $(FOBJ) $(LIBFT)

$(DOBJ)/%.o: $(DSRC)/%.c $(DINC)
		@$(MKDIR) $(DOBJ)
			$(CC) $(WFLAGS) -c $< $(FINCLIB) -o $@

libft:
		make -C $(DLIB)

clean:
		make -C $(DLIB) clean
			$(RM) $(DOBJ)

fclean: clean
		make -C $(DLIB) fclean
			$(RM) $(NAME)
			$(RM) libft_malloc.so

re: fclean all

.PHONY: all libft clean fclean re
