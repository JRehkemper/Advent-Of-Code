use std::fs;

fn main() {
    println!("Starting Calories-Manager:");

    let list = read_file();

    let calories_vector = list.split("\n").collect();

    let list_of_elves = calculate_calories_per_elf(calories_vector);

    //let (biggest_number_of_callories, number_of_elf) = order_elves_by_calories(&list_of_elves);

    let sorted_list = sort_list(list_of_elves);

    let sum = sum_of_three_biggest_elves(sorted_list);

    println!("The top 3 elves carry {} calories", sum);
    /*println!(
        "Take elf number {}. He has {} calories left.",
        number_of_elf + 1,
        biggest_number_of_callories
    );*/
}

fn read_file() -> String {
    let calories_list =
        fs::read_to_string("./src/calories_list.txt").expect("Should have read the file");

    return calories_list;
}

fn calculate_calories_per_elf(calories_vector: Vec<&str>) -> Vec<i32> {
    let mut list_of_elves: Vec<_> = Vec::new();
    let mut temp_sum: i32 = 0;
    for (_, line) in calories_vector.into_iter().enumerate() {
        if line == "" {
            list_of_elves.push(temp_sum);
            temp_sum = 0;
        } else {
            let single_number: i32 = line.parse().unwrap();
            temp_sum = temp_sum + single_number;
        }
    }

    list_of_elves
}

fn sort_list(list_of_elves: Vec<i32>) -> Vec<i32> {
    let mut sorted_list = list_of_elves;
    sorted_list.sort();
    let reversed_list: Vec<i32> = sorted_list.iter().copied().rev().collect();
    reversed_list
}

fn sum_of_three_biggest_elves(sorted_list: Vec<i32>) -> i32 {
    let elf1 = sorted_list[0];
    let elf2 = sorted_list[1];
    let elf3 = sorted_list[2];
    let sum: i32 = elf1 + elf2 + elf3;
    sum
}

fn order_elves_by_calories(list_of_elves: Vec<i32>) -> (i32, usize) {
    let biggest_number_of_callories: i32 = *list_of_elves.iter().max().unwrap();
    let number_of_elf = list_of_elves
        .iter()
        .position(|&r| r == biggest_number_of_callories)
        .unwrap();

    (biggest_number_of_callories, number_of_elf)
}
