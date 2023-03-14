// calculate how much money could possibly be created when a deposit is made using fractional reserve banking.
// all variables representing money are signed 64-bit integers in units of cents.

fn main() {
    let deposit: i64 = 10000;
    let reserve_rate: f64 = 0.10;
    println!("Your initial deposit is ${}", (deposit as f64)/100.0);
    println!("The bank's fractional reserve rate is {}%", reserve_rate*100.0);
    let money_created = calculate_money_created_from_deposit(deposit, reserve_rate);
    println!("The maximum possible money created from your deposit is ${}", (money_created as f64)/100.0);
    let total_money = deposit + money_created;
    println!("Total money that now exists is ${}", (total_money as f64)/100.0);
}

fn calculate_money_created_from_deposit(deposit:i64, reserve_rate:f64) -> i64 {
    println!("bank received deposit of ${}", (deposit as f64)/100.0);
    let amount_bank_can_lend: i64 = ((deposit as f64)*(1.0-reserve_rate)) as i64;
    if amount_bank_can_lend == deposit {
        return deposit;
    }
    if amount_bank_can_lend < 1 {
        return 0;
    }
    return amount_bank_can_lend + calculate_money_created_from_deposit(amount_bank_can_lend, reserve_rate);
}
