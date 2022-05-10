window.global = window

export function print(...args) {
    console.log(...args)
}

global.print = print
