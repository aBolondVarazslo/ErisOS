# AI Usage in ErisOS

## Overview
AI tools were used as an **assistant** during the development of ErisOS, primarily for non-code tasks.

**Important rules regarding AI:**
- AI-generated code **will not** be accepted in pull requests. Any PR containing clearly AI-generated code will be rejected.
- If you notice code in the repository that appears to be unedited AI output, please open an issue so it can be reviewed and replaced if necessary.
- AI may be used to help draft documentation and supporting files, but all content is reviewed and edited by the maintainer.

## What AI Has Helped With
- Structuring and wording of documentation files (README, CONTRIBUTING, CHANGELOG, etc.)
- Initial drafts for Markdown files

## What Was Done Manually
- All core architecture and design decisions
- **Every line of code** currently in the repository
- All debugging, testing, and hardware interaction work in emulators
- Final review and editing of all documentation

## Philosophy
AI is a supplementary tool, not a replacement for learning.  
**Preferred learning order:**
1. OSDev Wiki, books, and other human-written resources
2. Experimentation and debugging
3. AI assistance only when stuck

Understanding always comes first. AI should accelerate learning, never bypass it.

## Examples
- The initial structure and wording of [`README.md`](README.md) was drafted with AI help, then heavily reviewed and edited.
- [`CONTRIBUTING.md`](CONTRIBUTING.md) was initially drafted with AI because the author had limited experience writing contributor guidelines.

## Final Note
Using AI for smaller, non-critical files (especially documentation) is acceptable and encouraged when it improves clarity.  
**Using AI to generate core kernel code is not acceptable** for this project.
