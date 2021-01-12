# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 100
x = 0
counts = {}

def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(sys.argv[1], 'r') as csvfile:  # open csvfile in command-line arguement
        data = csv.reader(csvfile, delimiter=',')  # read csvfile into data
        for column in data:  # run once for each row in csvfile
            if column[0] != "team":  # don't add column names into either variable
                teams.append({"team": column[0], "rating": column[1]})  # append each team and their rating into the teams list as a dict
                counts.update({column[0]: 0})  # append each team name into counts as a key with initial value 0
    
    # Simulates N tournaments
    for x in range(N):
        simulate_tournament(teams)

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = int(team1["rating"])
    rating2 = int(team2["rating"])
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    winner = simulate_round(teams)  # get list of first round winners
    while len(winner) > 1:  # repeat round simulate until there is one winner
        winner = simulate_round(winner)  # simulate the new round with the previous rounds winners


    counts[winner[0]["team"]] = counts.get(winner[0]["team"]) + 1  # increment the winning teams win count
    return winner[0]["team"]

if __name__ == "__main__":
    main()
