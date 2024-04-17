type ops =
  { add : int
  ; sub : int
  ; mul : int
  ; div : int
  }

let rec dfs ops res rems =
  match rems with
  | [] -> res, res
  | hd :: tl ->
    let a1, a2 =
      if ops.add > 0
      then dfs { ops with add = ops.add - 1 } (res + hd) tl
      else Int.max_int, Int.min_int
    in
    let s1, s2 =
      if ops.sub > 0
      then dfs { ops with sub = ops.sub - 1 } (res - hd) tl
      else Int.max_int, Int.min_int
    in
    let m1, m2 =
      if ops.mul > 0
      then dfs { ops with mul = ops.mul - 1 } (res * hd) tl
      else Int.max_int, Int.min_int
    in
    let d1, d2 =
      if ops.div > 0
      then dfs { ops with div = ops.div - 1 } (res / hd) tl
      else Int.max_int, Int.min_int
    in
    ( Stdlib.min (Stdlib.min a1 s1) (Stdlib.min m1 d1)
    , Stdlib.max (Stdlib.max a2 s2) (Stdlib.max m2 d2) )
;;

let () =
  let _n = read_int () in
  let lst = String.split_on_char ' ' (read_line ()) |> List.map int_of_string in
  let ops =
    Scanf.scanf "%d %d %d %d" (fun a s m d -> { add = a; sub = s; mul = m; div = d })
  in
  let min_val, max_val = dfs ops (List.hd lst) (List.tl lst) in
  Printf.printf "%d\n%d" max_val min_val
;;
