use std::fs;
use std::fs::OpenOptions;
use std::error::Error;
use std::io::Write;


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

fn add_task(task: &str) -> std::io::Result<()> {


    let mut file = OpenOptions::new()
        .append(true) // Append mode
        .create(true) // Create if not exists
        .open("message.txt")?;

   write!(file, "\n{}", task)?; 
    Ok(())
}

fn main() {
    catch_error(read_tasks);
    catch_error(|| add_task("jeff"));
    catch_error(read_tasks);
}
