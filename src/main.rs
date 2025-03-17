use std::fs;
use std::fs::OpenOptions;
use std::error::Error;
use std::io::Write;
use std::io;


// Just run every func that returns a Result through this. 
fn catch_error<F, T, E>(method: F) 
where
    F: FnOnce() -> Result<T, E>, 
    E: std::fmt::Debug, {
    if let Err(e) = method() {
        eprintln!("Error: {:?}", e);
    }
}

fn read_tasks() -> Result<(), Box<dyn Error>> {
    let message: String = fs::read_to_string("message.txt")?;
    println!("{}", message);
    Ok(())
}

fn add_task(task: String) -> std::io::Result<()> {

let task_number_string = fs::read_to_string("config.txt")?;
let mut task_number: u32 = task_number_string.trim().parse().expect("Invalid number in file.");



    let mut file = OpenOptions::new()
        .append(true) // Append mode
        .create(true) // Create if not exists
        .open("message.txt")?;

   write!(file, "\n{}. {}", task_number, task)?; 

    task_number += 1;
    println!("{}", task_number);
    let mut file = OpenOptions::new()
        .create(true) // Create if not exists
        .truncate(true)
        .write(true)
        .open("config.txt")?;

   writeln!(file, "{}", task_number)?; 


    Ok(())
}




fn main() {
    //    catch_error(read_tasks);
    //    catch_error(|| add_task("jeff"));
    //    catch_error(read_tasks);
    loop {
//clearscreen::clear().expect("failed to clear screen");
        read_tasks();
        print!("tdl> ");
        io::stdout().flush().unwrap();
        let mut input = String::new();
        io::stdin().read_line(&mut input);

        let input = input.trim();

        if input.is_empty() {
            continue;
        }

        let args: Vec<&str> = input.split_whitespace().collect();

        match args.get(0) {
            Some(&"create") => {
                if let Some(task) = args.get(1..) {
                    let task_name = args.get(1..).map(|words| words.join(" ")).unwrap_or_else(|| "No task provided".to_string());
                    add_task(task_name.clone());
                    println!("Okay");
                    clearscreen::clear().expect("failed to clear screen");
                    println!("Added task {}:", task_name);
                    read_tasks();
                }
            }

            Some(&"exit") => {
                println!("Closing now.");
                break;
            }

            Some(&"help") => {
                println!("Possible commands are 'help','exit', and 'create <task>'")
            }
            _ => {
                println!("Unknown command. Available commands: create, del, exit");
            }
        }


    }
}
