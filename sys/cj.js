window.global = window

export function print(...args) {
    console.log(...args)
}

export function str(o) {
    return o.toString()
}

global.print = print
global.str = str
