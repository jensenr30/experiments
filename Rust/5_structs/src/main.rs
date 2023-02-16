fn main() {
    // create some structures
    let mut u = build_user(String::from("user"), String::from("user@gmail.com"));
    print_user(&u);
    u.active = true;
    print_user(&u);
    // create a new structure with some new data, the rest of the data gets copied from the old struct.
    let u2 = User {
        username: String::from("bob"),
        email: String::from("bob@cia.gov"),
        ..u
    };
    print_user(&u2);
    
    // make some tuple structs
    let red = Color(255, 0, 0);
    let origin = Point(0.0, 0.0, 0.0);
    println!("Red = ({}, {}, {}).",red.0, red.1, red.2);
    println!("Origin = ({}, {}, {}).",origin.0, origin.1, origin.2);

    // create a rectangle struct
    let rect1 = Rectangle {
        width: 20,
        height: 50,
    };
    let rect2 = Rectangle {
        width: 10,
        height: 60,
    };
    let rect3 = Rectangle {
        width: 15,
        height: 40,
    };
    let rect4 = Rectangle::square(20);
    dbg!(&rect1);
    dbg!(&rect2);
    dbg!(&rect3);
    dbg!(&rect4);
    println!("The area of rectangle is {} square units.", rect1.area());
    println!("Question: will rect2 fit in rect1? Answer: {}",rect1.can_hold_yes_no(&rect2));
    println!("Question: will rect3 fit in rect1? Answer: {}",rect1.can_hold_yes_no(&rect3));
    println!("Question: will rect4 fit in rect1? Answer: {}",rect1.can_hold_yes_no(&rect4));
}

// fn area(rect: &Rectangle) -> u32 {
//     rect.width * rect.height
// }

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

impl Rectangle {
    fn square(size: u32) -> Self {
        Self {
            width: size,
            height: size,
        }
    }
    fn area(&self) -> u32 {
        self.width * self.height
    }
    fn can_hold(&self, other: &Rectangle) -> bool {
        (self.width >= other.width) && (self.height >= other.height)
    }
    fn can_hold_yes_no(&self, other: &Rectangle) -> &str {
        if self.can_hold(other) {return "yes"} else {return "no"}
    }
}
