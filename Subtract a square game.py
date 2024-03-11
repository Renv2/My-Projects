# Import modules
import math
import random


# Test if the input of the user is integer number
def test_if_input_int(num):
    x = num.isnumeric()
    if x:
        return int(num)
    else:
        return False


# Game Playing
def game_play(y):
    current_Player = 1
    while y > 0:
        move = test_if_input_int(input(f'Player {current_Player}: Please take a square number of coins: '))
        # See if move is a square number bigger than 0 and less than number of remaining coins
        if y >= move > 0 and math.sqrt(move) % 1 == 0:
            y -= move
            if y <= 0:
                print(f'Player {current_Player} is winner.')
                a = input('Press enter to exit.')
                exit()
                # Exit the game when a player wins
            print(f'Now we have {y} coins.')
            current_Player = 3 - current_Player
            # Switch between players
        else:
            print('Please enter a valid number.')
            continue


# Welcome message and choosing number of coins
print('')
print('Welcome to subtract a square game')
print('In this game two players take turns subtracting a square number of coins')
print('from a pile of coins and whoever takes the last coin wins')
print('')
print('If you want to choose number of coins between 10 and 1000 enter <1>')
print('If you want a random number of coins enter <2>')
print('If you want to exit the game enter <3>')
while True:
    choice = test_if_input_int(input())
    if choice == 1 or choice == 2:

        while choice == 1:
            print('Enter number of coins: ')
            n_coins = test_if_input_int(input())
            while n_coins:
                if 10 < n_coins < 1000 and math.sqrt(n_coins) % 1 != 0:
                    game_play(n_coins)
                else:
                    break
            print('Please enter a valid number.')

        while choice == 2:
            n_coins = random.randint(10, 1000)
            # Generate random number of coins
            if math.sqrt(n_coins) % 1 != 0:
                print(f'Number of coins is {n_coins}')
                game_play(n_coins)

    elif choice == 3:
        break
    else:
        print('Please enter a valid choice.')
        continue

