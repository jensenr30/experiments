const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;

fn main() {
    // mutability
    let mut x = 5;
    println!("The value of x is {x}.");
    x = 6;
    println!("The value of x is {x}.");
    println!("3 hours in seconds is {THREE_HOURS_IN_SECONDS} seconds.");
    
    // scope and variable shadowing
    let x = 3;
    println!("x = {x}.");
    let x = x + 1;
    println!("x = {x}.");
    {
        let x = x * 2;
        println!("x = {x}. {{inner scope}}");
    }
    println!("x = {x}. {{main() scope}}");

    // 'let' keyword effectively creates new variable with same name
    let spaces = "  ";
    let spaces = spaces.len();
    println!("spaces = {spaces}.");

    // trying to change type of mutable variable produces type error
    //let mut spaces = "  ";
    //spaces = spaces.len();

}
