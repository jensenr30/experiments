fn main() {
    // create some structures
    let mut u = build_user(String::from("user"), String::from("user@gmail.com"));
    print_user(&u);
    u.active = true;
    print_user(&u);
    // create a new structure with some new data, the rest of the data gets copied from the old struct.
    let u2 = User {
        username: String::from("mkultra"),
        email: String::from("mkultra@cia.gov"),
        ..u
    };
    print_user(&u2);
    
    // make some tuple structs
    let red = Color(255, 0, 0);
    let origin = Point(0.0, 0.0, 0.0);
    println!("Red = ({}, {}, {}).",red.0, red.1, red.2);
    println!("Origin = ({}, {}, {}).",origin.0, origin.1, origin.2);

    // create a rectangle struct
    let scale:u32 = 2;
    let rect = Rectangle{
        width: dbg!(20*scale),
        height: dbg!(50*scale),
    };
    println!("rectangle is {:#?}",rect);
    println!(
        "The area of rectangle is {} square units.",
        area(&rect)
    );
    dbg!(&rect);
}

fn area(rect: &Rectangle) -> u32 {
    rect.width * rect.height
}

struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

fn build_user(username: String, email: String) -> User {
    println!("Creating new user \"{username}\"...");
    return User {
        active: false,
        username,
        email,
        sign_in_count: 0,
    };
}

fn print_user(u: &User) {
    println!("active = {}", u.active);
    println!("username = {}", u.username);
    println!("email = {}", u.email);
    println!("sign_in_count = {}", u.sign_in_count);
}

struct Color(u8, u8, u8);
struct Point(f64, f64, f64);

#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}