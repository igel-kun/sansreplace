use std::{
    fs::OpenOptions,
    hint::black_box,
    path::Path,
    time::{Duration, Instant},
};

use anyhow::{Context, Result};
use csv::WriterBuilder;
use rand::{rngs::SmallRng, SeedableRng};

mod algorithms;

fn time_test<F>(f: F, length: usize, amount: usize) -> std::time::Duration
where
    F: Fn(&mut SmallRng, usize, &mut [usize]),
{
    assert!(amount <= length);
    let mut rng = SmallRng::from_entropy();
    let mut v = vec![0; amount];
    let mut iters = 1;
    let mut remaining = std::time::Duration::from_millis(500);
    loop {
        let now = Instant::now();
        for _ in 0..iters {
            f(&mut rng, length, &mut v);
            black_box(&v);
        }
        let t = now.elapsed();
        if remaining < t {
            return t.checked_div(iters).unwrap();
        }
        remaining -= t;
        if remaining < t {
            return t.checked_div(iters).unwrap();
        }
        let ratio = remaining.as_secs_f64() / t.as_secs_f64();
        if ratio <= 60.0 {
            iters = ((iters as f64) * ratio) as u32;
        } else {
            iters *= 3;
        }
    }
}

fn write_row(name: &str, n: usize, k: usize, t: Duration) -> Result<()> {
    let path = Path::new("/tmp/FIXME.csv");
    let f = OpenOptions::new()
        .create(true)
        .append(true)
        .open(path)
        .with_context(|| format!("Opening file {}", path.display()))?;
    let mut wtr = WriterBuilder::new().from_writer(f);
    wtr.serialize(("result", name, n, k, t.as_secs_f64()))?;
    Ok(())
}

fn main() -> Result<()> {
    const MAX: usize = 1_000_000_000;
    const MAXTIME: Duration = Duration::from_secs(3);
    for (name, f) in algorithms::algorithms().iter() {
        let mut kk = (1, 1);
        'kk: while kk.1 < MAX {
            let mut nn = kk;
            while nn.1 < MAX {
                let t = time_test(f, nn.1, kk.1);
                write_row(name, nn.1, kk.1, t)?;
                println!("{} {} {}: {:?}", name, nn.1, kk.1, t);
                if t > MAXTIME {
                    if nn == kk {
                        break 'kk;
                    } else {
                        break;
                    }
                }
                nn = (nn.1, nn.0 + nn.1);
            }
            kk = (kk.1, kk.0 + kk.1);
        }
    }
    Ok(())
}
