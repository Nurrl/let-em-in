# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lroux <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 14:23:48 by lroux             #+#    #+#              #
#    Updated: 2019/01/14 13:46:33 by lroux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT	:= let-em-in
NAME	:= lem-in

SRCDIR	:= srcs
OBJDIR	:= objs
INCDIR	:= incs

SRCS	:= let-em-in.c

LIBS	:= libft libpf
LIBDIR	:= libs

# Include core
include $(LIBDIR)/project.mk


