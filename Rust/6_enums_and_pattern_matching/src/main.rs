#![allow(unused)]

use std::string;
fn main() {
    // enums
    let home = IpAddr::V4(127, 0, 0, 1);
    let loopback = IpAddr::V6(String::from("::1"));
    route(home);
    route(loopback);
    let m = Message::Write(S("hello"));
    m.call();
    // Option<T>, Some(T), and None.
    let x = Some(5);
    let y: Option<i32> = None;
    //println!("x * y = {}",x*y);
    println!("The value of a quarter is {} cents.", value_in_cents(Coin::Quarter));
}

enum IpAddr {
    V4(u8, u8, u8, u8),
    V6(String),
}

fn route(ip_kind: IpAddr) {
    println!("Routing to IP address ");
}

enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        // method body would be defined here.
    }
}

fn S(string_literal: &str) -> String {
    String::from(string_literal)
}

fn optional_add(x: Option<i32>, y: Option<i32>) {
    
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin:Coin) -> u64 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}