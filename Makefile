# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/06/25 18:44:34 by pabmart2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
DEBUG_FLAGS = -g -fno-inline -gdwarf-4
ASAN_FLAGS = $(DEBUG_FLAGS) -fsanitize=address
TSAN_FLAGS = $(DEBUG_FLAGS) -fsanitize=thread
BUILD_DIR = build

OBJ_DIR = build/obj

NAME = philo

HEADERS = \
	philo/include/philosophers.h \
	philo/include/colors.h

SRC = \
	philo/src/main.c \
	philo/src/philo_behaviour/philo_behaviour.c \
	philo/src/philo_behaviour/philo_death.c \
	philo/src/philo_behaviour/philo_eat_utils.c \
	philo/src/philo_behaviour/philo_eat.c \
	philo/src/philo_behaviour/philo_monitor.c \
	philo/src/philo_behaviour/philo_sleep_think.c \
	philo/src/philo_behaviour/philo_start.c \
	philo/src/utils/get_time_ms.c \
	philo/src/utils/arg_check.c \
	philo/src/utils/usleep_check.c \
	philo/src/utils/mutex_operations/get_philo_status.c \
	philo/src/utils/mutex_operations/get_simulation_running.c \
	philo/src/utils/mutex_operations/safe_mutex.c \
	philo/src/utils/mutex_operations/safe_printf.c \
	philo/src/utils/mutex_operations/set_philo_status.c \
	philo/src/utils/mutex_operations/set_simulation_running.c \
	philo/src/utils/args_parse/ft_atol.c \
	philo/src/utils/args_parse/ft_atoui.c \
	philo/src/utils/args_parse/ft_isdigit.c \
	philo/src/utils/args_parse/ft_isspace.c \
	philo/src/utils/philo_list_helpers/add_philo.c \
	philo/src/utils/philo_list_helpers/clean_philos.c \
	philo/src/utils/philo_list_helpers/create_philo.c \
	philo/src/utils/philo_list_helpers/get_philo.c \
	philo/src/utils/philo_list_helpers/philo_populate.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INCLUDES = \
	-Iphilo/include \

all: $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(NAME)

debug-asan: CFLAGS += $(ASAN_FLAGS)
debug-asan: clean $(NAME)

debug-tsan: CFLAGS += $(TSAN_FLAGS)
debug-tsan: clean $(NAME)

HELGRIND_CC = gcc
HELGRIND_FLAGS = -g -gdwarf-4 -fno-inline

debug-helgrind: CC := $(HELGRIND_CC)
debug-helgrind: CFLAGS := $(HELGRIND_FLAGS) $(CFLAGS)
debug-helgrind: clean $(NAME)



clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mObject files removed\033[0m"

fclean: clean
	@rm -f $(BUILD_DIR)/$(NAME)
	@echo "\033[31m$(NAME) removed\033[0m"

re: fclean
	$(MAKE) all

$(NAME): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)/$(NAME)  $(INCLUDES)
	@echo "\033[32m\n¡$(NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\n"

$(OBJ) : $(OBJ_DIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[34mCompiling: \033[0m$<"

#################################### BONUS #####################################

# Variables para el bonus
BONUS_BUILD_DIR = build
BONUS_OBJ_DIR = build/obj_bonus
BONUS_NAME = philo_bonus
BONUS_HEADERS = \
	philo_bonus/include/philosophers_bonus.h \
	philo_bonus/include/colors_bonus.h
BONUS_SRC = \
	philo_bonus/src/main_bonus.c \
	philo_bonus/src/philo_behaviour/philo_behaviour_bonus.c \
	philo_bonus/src/philo_behaviour/philo_eat_bonus.c \
	philo_bonus/src/philo_behaviour/philo_monitor_bonus.c \
	philo_bonus/src/philo_behaviour/philo_sleep_think_bonus.c \
	philo_bonus/src/philo_behaviour/philo_start_bonus.c \
	philo_bonus/src/utils/get_time_ms_bonus.c \
	philo_bonus/src/utils/arg_check_bonus.c \
	philo_bonus/src/utils/args_parse/ft_atol_bonus.c \
	philo_bonus/src/utils/args_parse/ft_atosize_t_bonus.c \
	philo_bonus/src/utils/args_parse/ft_atoui_bonus.c \
	philo_bonus/src/utils/args_parse/ft_isdigit_bonus.c \
	philo_bonus/src/utils/args_parse/ft_isspace_bonus.c \
	philo_bonus/src/philo_helpers/clean_philo_bonus.c \
	philo_bonus/src/philo_helpers/create_philo_bonus.c \
	philo_bonus/src/philo_helpers/philo_populate_bonus.c
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SRC:.c=.o))
BONUS_INCLUDES = -Iphilo_bonus/include

bonus: $(BONUS_NAME)
	@echo "\033[35mBonus compiled!\033[0m"

$(BONUS_NAME): $(BONUS_OBJ)
	@mkdir -p $(BONUS_BUILD_DIR)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_BUILD_DIR)/$(BONUS_NAME) $(BONUS_INCLUDES)
	@echo "\033[32m\n¡$(BONUS_NAME) compiled! ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\n"

$(BONUS_OBJ) : $(BONUS_OBJ_DIR)/%.o : %.c $(BONUS_HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@
	@echo "\033[34mCompiling bonus: \033[0m$<"

bonus-clean:
	@rm -rf $(BONUS_OBJ_DIR)
	@echo "\033[31mBonus object files removed\033[0m"

bonus-fclean: bonus-clean
	@rm -f $(BONUS_BUILD_DIR)/$(BONUS_NAME)
	@echo "\033[31m$(BONUS_NAME) removed\033[0m"

bonus-re: bonus-fclean
	$(MAKE) bonus

################################################
.PHONY: all debug debug-asan debug-tsan debug-helgrind clean fclean re bonus bonus-clean bonus-fclean bonus-re
