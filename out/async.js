// source file: prog/async.cj
import '../sys/cj.js'
/* 0  */	import * as sqlite from 'https://deno.land/x/sqlite/mod.ts';
/* 3  */	let db=new sqlite.DB('test.db');
/* 4  */	db.query('CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)');
/* 6  */	let names=['Peter Parker','Clark Kent','Bruce Wayne'];
/* 9  */	for (let name of names) db.query('INSERT INTO people (name) VALUES (?)',[name]);;
/* 13 */	for (let r of db.query('SELECT id, name FROM people')) print(r[0],r[1]);;
/* 17 */	db.close();
