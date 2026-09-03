# M0 Design and Understanding Note

Answer briefly in your own words. This is not intended to be a long report.

1. What responsibility belongs to `Workspace`, and what responsibilities belong to `Document`, `Prompt`, and `Message` instead?
 
 Workspace is where we will have our central object and is used for organization because it owns the other 3 types, preserves insertion order, and has buonds-checked access to single items. It doesn't care about the internal fields it only stores them, counts them, and hands the references back out.

 Prompt is responsible for holding a reusable instruction. A prompt is a small value type that is a reusable named block of instruction text for later AI-assisted work. In m0, it only holds data and doesn't send anything to a llm

 Message refers to the actual dialogue that we will have later on with the llm. It will one turn in an actual back and forth conversation with LLM (for now it just holds one piece of data which is one role-tagged conversation turn)

2. Why are the collections inside `Workspace` private? Explain the purpose of the const and non-const `At` overloads.

So that workspace fully controls how items are added and accessed so callers can't reach in and reorder or erase from vectors. 

3. Explain one meaningful test you added. What behavior does it check, and what implementation error could it catch?

'document_load_failure_preserves_state' calls load() with a path that doesn't exist, then asserts the Document's title, sourcePath, and contents are all identical to what they were before the call. This checks that a failed load() must leave the existing Document completely unchanged



4. Describe one implementation decision that you verified, tested, or revised before submitting your work.

I made sure all file-reading happens in local variables and that the object's actual member variables are only assigned after the read has fully succeeded. I verified this by writing document_load_failure_preserves_state(), which constructs a Document with
known data, calls load() on an invalid path, and asserts none of the three
fields changed.


5. If generative AI was used, disclose it as required by course policy. If no generative AI was used, state that. The disclosure itself is not used as proof of authorship or understanding.

Generative AI was used to improve code comments and provide clearer comment summaries but not for coding. 

For example, I asked it to write a comment describing how the compiler automatically picks which doc prompt or message to use and it said // The compiler automatically picks which documentAt/promptAt/messageAt to use, based on whether the Workspace instance being called on is const at that point in the code, this isn't chosen manually anywhere.

 However, I did not leave it like this and I went in and simplified it down into my own words. I just used it to clarify and make sure my comments included everything I wanted it to include.