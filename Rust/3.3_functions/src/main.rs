fn main() {
    let x = 5;
    f1(x);
    let label = "hours".trim();
    print_labeled_value(x, label);
    println!("");

    let condition = true;
    let number = if condition { 5 } else { 6 };
    println!("number = {number}");
    let mut x = 0;
    let result = loop {
        println!("x = {x}");
        if x >= 10 {
            break x * -2;
        }
        else {
            x += 1;
        }
    };
    println!("loop broke at x = {x}");
    println!("result = {result}");
    println!("{}",five());
    test_loops();

    let mut i = 0;
    while i <= 5 {
        i += 1;
        println!("i = {i}");
    }

    let a = [10, 20, 30, 40, 50];
    for element in a {
        println!("{element}");
    }

    for s in (0..=5).rev() {
        println!("T-0:0{s}...")
    }
    println!("LIFTOFF!");

    let tdoc = [
        ("first", "partridge in a pear tree"), 
        ("second", "turtle doves"),
        ("third", "french hens"),
        ("fourth", "calling birds"),
        ("fifth", "golden rings"),
        ("sixth", "geese a-laying"),
        ("seventh", "swans a-swimming"),
        ("eighth", "maids a-milking"),
        ("ninth", "ladies dancing"),
        ("tenth", "lords a-leaping"),
        ("eleventh", "pipers piping"),
        ("twelfth", "drummers drumming"),
        
    ];
    for d in 0..tdoc.len() {
        println!("On the {} day of Christmas, my true love sent to me:", tdoc[d].0);
        for i in (1..=d).rev() {
            println!("{} {}", i+1, tdoc[i].1);
        }
        if d > 0 {
            print!("And a ");
        }
        else {
            print!("A ");
        }
        println!("{}\n", tdoc[0].1);
    }
}

fn f1(x: i32) {
    println!("[f1] The value is {x}.");
}

fn print_labeled_value(value: i32, label: &str) {
    print!("{value} {label}");
}

fn five() -> i32 {
    return 5;
}

fn test_loops() {
    let mut i = 0;
    let mut j = 0;
    'loop1: loop {
        loop {
            println!("{i}{j}");
            j += 1;
            if j >= 3 {
                j = 0;
                i += 1;
            }
            if i >= 3 {
                break 'loop1;
            }
        }
    }
}