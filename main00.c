/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:06:07 by mbany             #+#    #+#             */
/*   Updated: 2024/12/13 19:23:33 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Potrzebne dla strcmp i innych operacji na ciągach znaków
#include <unistd.h> // Potrzebne dla funkcji chdir
#include <readline/readline.h>
#include <readline/history.h>

// Funkcja do wczytywania komendy z readline
char *get_command(void) 
{
    // Wyświetl prompt i wczytaj linię
    char *command = readline("$ ");
    // Jeśli wprowadzono komendę, dodaj ją do historii
    if (command != NULL && command[0] != '\0')
    {
        add_history(command);
    }
    return (command); // readline alokuje pamięć, którą musimy później zwolnić
}

// Funkcja do obsługi polecenia "pwd"
void handle_pwd_command(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Aktualny katalog: %s\n", cwd);
    }
    else
    {
        perror("Blad uzyskania sciezki biezacego katalogu");
    }
}

// Funkcja do obsługi polecenia "cd .."
void handle_cd_back_command(void)
{
    if (chdir("..") == 0)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("Przeniesiono do katalogu nadrzednego: %s\n", cwd);
        }
        else
        {
            perror("Blad uzyskania sciezki po zmianie katalogu");
        }
    }
    else
    {
        perror("Blad podczas przechodzenia do katalogu nadrzednego");
    }
}

int main(void)
{
    char *command;

    while (1)
    {
        // Pobierz komendę od użytkownika
        command = get_command();
        // Jeśli komenda jest NULL (np. EOF), zakończ program
        if (command == NULL)
        {
            printf("exit\n");
            break;
        }

        // Sprawdź, czy polecenie to "pwd"
        if (strcmp(command, "pwd") == 0)
        {
            handle_pwd_command();
        }
        // Sprawdź, czy polecenie to "cd .."
        else if (strcmp(command, "cd ..") == 0)
        {
            handle_cd_back_command();
        }
        else
        {
            // Wydrukuj wprowadzoną komendę (do debugowania)
            printf("Wprowadzone polecenie: %s\n", command);
        }

        // Zwróć pamięć po komendzie
        free(command);
    }
    // Wyczyść historię przed zakończeniem programu
    rl_clear_history();
    return (0);
}


// wywołanie programu: cc main.c -lreadline -lhistory -lncurses
