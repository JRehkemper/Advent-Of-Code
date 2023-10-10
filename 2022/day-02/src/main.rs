use std::fs;

fn main() {
    let puzzle_input: String = read_file("./puzzle_input.txt");
    let puzzle_lines: Vec<&str> = puzzle_input.split("\n").collect();
    let mut total_score = 0;
    for line in puzzle_lines {
        if line == "" {
            continue;
        }

        println!("{}", line);
        let (your_pick, my_pick) = get_picks(line);

        let score;
        let my_pick_score = score_for_my_pick(&my_pick);
        let your_pick_score = score_for_your_pick(&your_pick);
        let game_score = score_of_game(my_pick_score, your_pick_score);

        score = my_pick_score + game_score;

        total_score += score;
        println!("Your score: {}", score);
    }

    println!("Your total score is: {}", total_score);
}

fn read_file(filename: &str) -> String {
    let content = fs::read_to_string(filename).expect("Should read the file");
    content
}

fn get_picks(line: &str) -> (String, String) {
    let picks: Vec<&str> = line.split(" ").collect();
    let your_pick = picks[0];
    let result = picks[1];

    let my_pick = calculate_my_pick(your_pick, result);

    (String::from(your_pick), String::from(my_pick))
}

/*
 * A: Rock
 * B: Paper
 * C: Scissors
 * X: Lose
 * Y: Draw
 * Z: Win
 */
fn calculate_my_pick(your_pick: &str, result: &str) -> String {
    if your_pick == "A" {
        if result == "X" {
            String::from("Z")
        } else if result == "Y" {
            String::from("X")
        } else {
            String::from("Y")
        }
    } else if your_pick == "B" {
        if result == "X" {
            String::from("X")
        } else if result == "Y" {
            String::from("Y")
        } else {
            String::from("Z")
        }
    } else {
        if result == "X" {
            String::from("Y")
        } else if result == "Y" {
            String::from("Z")
        } else {
            String::from("X")
        }
    }
}

fn score_for_my_pick(my_pick: &str) -> i32 {
    let sum = match my_pick {
        "X" => 1,
        "Y" => 2,
        "Z" => 3,
        _ => 0,
    };

    sum
}

fn score_for_your_pick(your_pick: &str) -> i32 {
    let sum = match your_pick {
        "A" => 1,
        "B" => 2,
        "C" => 3,
        _ => 0,
    };

    sum
}

fn score_of_game(my_pick: i32, your_pick: i32) -> i32 {
    let mut score = 0;
    if my_pick == 1 {
        if your_pick == 1 {
            score = 3;
        } else if your_pick == 2 {
            score = 0;
        } else if your_pick == 3 {
            score = 6;
        }
    } else if my_pick == 2 {
        if your_pick == 1 {
            score = 6;
        } else if your_pick == 2 {
            score = 3;
        } else if your_pick == 3 {
            score = 0;
        }
    } else if my_pick == 3 {
        if your_pick == 1 {
            score = 0;
        } else if your_pick == 2 {
            score = 6;
        } else if your_pick == 3 {
            score = 3;
        }
    }

    score
}
