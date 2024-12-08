
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *rl;
    rl = readline("Prompt > ");
    printf("%s\n", rl);
    return (0);
}
/*
Skompilowanie i uruchomienie tego programu spowoduje pojawienie się poniższych efektów.

Kopia
$> ./minishell
Prompt > Hi ! How are you ?
Hi ! How are you ?
$>
*/
